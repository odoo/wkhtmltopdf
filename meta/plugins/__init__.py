import os
import logging

from pathlib import Path
from typing import Any
from cutekit import cli, shell, model, jexpr, vt100, ensure, pods

ensure((0, 7, 0))

_logger = logging.getLogger(__name__)

_dataCache: dict[str, Any] = {}


def loadData(name: str) -> jexpr.Json:
    global _dataCache
    if name not in _dataCache:
        _dataCache[name] = jexpr.read(Path(f"meta/data/{name}.json"))
    return _dataCache[name]


pods.IMAGES["ubuntu"].setup += [
    f"apt -y install {' '.join(loadData('pod-ubuntu')['requires'] + loadData('pod-ubuntu')['devRequires'])}"
]
pods.IMAGES["debian"].setup += [
    f"apt -y install {' '.join(loadData('pod-debian')['requires'] + loadData('pod-debian')['devRequires'])}"
]
pods.IMAGES["alpine"].setup += [
    f"apk add {' '.join(loadData('pod-alpine')['requires'] + loadData('pod-alpine')['devRequires'])}"
]
pods.IMAGES["arch"].setup += [
    f"pacman --noconfirm -S {' '.join(loadData('pod-arch')['requires'] + loadData('pod-arch')['devRequires'])}"
]
pods.IMAGES["fedora"].setup += [
    f"dnf -y install {' '.join(loadData('pod-fedora')['requires'] + loadData('pod-fedora')['devRequires'])}"
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


@cli.command("w", "wk", "Build system for wkhtmltopdf")
def _(args: cli.Args):
    pass


@cli.command("c", "wk/configure", "Configure wkhtmltopdf")
def _(args: cli.Args):
    model.Project.use(args)
    target = useTarget(args)
    prefix = usePrefix(args, target)

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


@cli.command("b", "wk/build", "Build wkhtmltopdf")
def _(args: cli.Args):
    model.Project.use(args)
    target = useTarget(args)
    prefix = usePrefix(args, target)

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


def package():
    pass


@cli.command("p", "wk/profile", "Profile wkhtmltopdf")
def _(args: cli.Args):
    target = useTarget(args)
    prefix = os.path.relpath(usePrefix(args, target))
    what = args.consumeOpt("what", "cpu")
    rate = args.consumeOpt("rate", 1000)
    wkhtmltopdf = os.path.join(prefix, "bin/wkhtmltopdf")
    shell.profile([wkhtmltopdf] + args.extra, rate=rate, what=what)
