import os
import sys
import logging
import platform

from pathlib import Path
from typing import Any
from cutekit import cli, shell, model, jexpr, vt100, ensure, pods, const

ensure((0, 7, 0))

_logger = logging.getLogger(__name__)

_dataCache: dict[str, Any] = {}


def loadData(name: str) -> jexpr.Json:
    global _dataCache
    if name not in _dataCache:
        _dataCache[name] = jexpr.read(Path(f"meta/data/{name}.json"))
    return _dataCache[name]

pods.IMAGES["ubuntu-jammy"].setup += [
    f"apt -y install {' '.join(loadData('pod-ubuntu-jammy')['requires'] + loadData('pod-ubuntu-jammy')['devRequires'])}",
    "gem install fpm",
]
pods.IMAGES["debian-bookworm"].setup += [
    f"apt -y install {' '.join(loadData('pod-debian-bookworm')['requires'] + loadData('pod-debian-bookworm')['devRequires'])}",
    "gem install fpm",
]
pods.IMAGES["alpine-3.18"].setup += [
    f"apk add {' '.join(loadData('pod-alpine-3.18')['requires'] + loadData('pod-alpine-3.18')['devRequires'])}",
    "gem install fpm",
]
pods.IMAGES["arch"].setup += [
    f"pacman --noconfirm -S {' '.join(loadData('pod-arch')['requires'] + loadData('pod-arch')['devRequires'])}",
    "gem install fpm",
]
pods.IMAGES["fedora-39"].setup += [
    f"dnf -y install {' '.join(loadData('pod-fedora-39')['requires'] + loadData('pod-fedora-39')['devRequires'])}",
    "gem install fpm",
]


def useTarget(args: cli.Args) -> model.Target:
    target = model.Target(str(args.consumeOpt("target", "host")))
    target.props["host"] = True
    _logger.debug(f"Using target '{target.id}'")
    return target


def usePrefix(args: cli.Args, target: model.Target) -> str:
    default = os.path.join(target.builddir, "prefix")
    prefix = str(args.consumeOpt("prefix", default))
    prefix = os.path.abspath(prefix)
    if not os.path.exists(prefix):
        os.makedirs(prefix)
    _logger.debug(f"Using prefix '{prefix}'")
    return prefix


QT = loadData("configure")


def wkConfigure(target: model.Target, prefix: str) -> None:
    qtBuildir = shell.mkdir(os.path.join(target.builddir, "qt"))
    if not shell.exec(
        os.path.abspath("./qt/configure"),
        *QT,
        f"--prefix={prefix}",
        "-v",
        cwd=qtBuildir,
    ):
        raise RuntimeError("Failed to configure Qt")

    print(f"{vt100.GREEN + vt100.BOLD}Configured Yaii~ :3{vt100.RESET}")


def wkBuild(target: model.Target, prefix: str) -> None:
    qtBuildir = shell.mkdir(os.path.join(target.builddir, "qt"))
    if not shell.exec("make", "-j", str(shell.nproc()), cwd=qtBuildir):
        raise RuntimeError("Failed to build Qt")

    print(f"{vt100.GREEN + vt100.BOLD}Built Qt :3{vt100.RESET}")

    if not shell.exec("make", "install", cwd=qtBuildir):
        raise RuntimeError("Failed to install Qt")

    print(f"{vt100.GREEN + vt100.BOLD}Installed Qt :3{vt100.RESET}")

    wkBuildir = shell.mkdir(os.path.join(target.builddir, "wk"))
    qmake = os.path.join(prefix, "bin/qmake")
    wkpro = os.path.abspath("wkhtmltopdf.pro")

    if not shell.exec(qmake, wkpro, cwd=wkBuildir):
        raise RuntimeError("Failed to configure wkhtmltopdf")

    print(f"{vt100.GREEN + vt100.BOLD}Configured wkhtmltopdf :3{vt100.RESET}")

    if not shell.exec(
        "make",
        "install",
        f"INSTALL_ROOT={prefix}",
        "-j",
        str(shell.nproc()),
        cwd=wkBuildir,
    ):
        raise RuntimeError("Failed to install wkhtmltopdf")

    print(f"{vt100.GREEN + vt100.BOLD}Installed wkhtmltopdf :3{vt100.RESET}")

    print(
        f"{vt100.GREEN + vt100.BOLD}Finyished buiwding t-to '{prefix}' :3{vt100.RESET}"
    )


@cli.command("w", "wk", "Build system for wkhtmltopdf")
def _(args: cli.Args):
    pass


@cli.command("c", "wk/configure", "Configure wkhtmltopdf")
def _(args: cli.Args):
    model.Project.use(args)
    target = useTarget(args)
    prefix = usePrefix(args, target)

    wkConfigure(target, prefix)


@cli.command("b", "wk/build", "Build wkhtmltopdf")
def _(args: cli.Args):
    model.Project.use(args)
    target = useTarget(args)
    prefix = usePrefix(args, target)

    wkBuild(target, prefix)


@cli.command("p", "wk/profile", "Profile wkhtmltopdf")
def _(args: cli.Args):
    target = useTarget(args)
    prefix = os.path.relpath(usePrefix(args, target))
    what = args.consumeOpt("what", "cpu")
    rate = args.consumeOpt("rate", 1000)
    wkhtmltopdf = os.path.join(prefix, "bin/wkhtmltopdf")
    shell.profile([wkhtmltopdf] + args.extra, rate=rate, what=what)


@cli.command("d", "wk/dist", "Distribute wkhtmltopdf")
def _(args: cli.Args):
    # This command will configure, build, install and
    # package wkhtmltopdf for distribution.

    model.Project.use(args)
    target = useTarget(args)
    prefix = "/"
    distro = args.consumeOpt("distro", None)
    if distro is None:
        import sys

        print(sys.argv)
        raise RuntimeError("No distro specified")

    version = args.consumeOpt("version", None)
    if version is None:
        with open("VERSION") as f:
            version = f.read().strip()
    flavor = args.consumeOpt("flavor", "dev")

    wkConfigure(target, prefix)
    wkBuild(target, prefix)
    # Use FPM to package wkhtmltopdf
    dist = Path(const.PROJECT_CK_DIR) / "dist"
    dist.mkdir(exist_ok=True)

    distro = loadData("pod-" + distro)
    arch = platform.machine()
    output = f"odoo-wkhtmltopdf-{distro['id']}-{arch}-{version}-{flavor}.{distro['extension']}"

    # Make sure fpm is in the PATH
    try:
        GEM_HOME = shell.popen("gem", "env", "user_gemhome")
        print(f"Using GEM_HOME={GEM_HOME}")
        os.environ["PATH"] = f'{GEM_HOME}/bin:{os.environ["PATH"]}'
    except:
        pass # Some distros don't have bin installed in user gemhome

    shell.exec(
        "fpm",
        "--license",
        "LGPLv3",
        "--vendor",
        "Odoo S.A.",
        "--url",
        "https://github.com/odoo/wkhtmltopdf",
        "--maintainer",
        "Nicolas V. <nivb@odoo.com>",
        "-s",
        "dir",
        "-t",
        distro["package"],
        "-n",
        "odoo-wkhtmltopdf",
        "-v",
        f"{version}-{flavor}",
        "-C",
        prefix,
        "-p",
        str(dist / output),
        "/bin/wkhtmltopdf",
    )
