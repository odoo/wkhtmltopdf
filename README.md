wkhtmltopdf and wkhtmltoimage
-----------------------------

> [!IMPORTANT]
> This is a fork of the original wkhtmltopdf project tailored for use with
> Odoo. It is not intended for general use. If you are looking for the
> original project, please see https://github.com/wkhtmltopdf/wkhtmltopdf

wkhtmltopdf and wkhtmltoimage are command line tools to render HTML into PDF
and various image formats using the QT Webkit rendering engine. These run
entirely "headless" and do not require a display or display service.

See https://wkhtmltopdf.org for updated documentation.

# Building

```bash
$ ./bootstrap.sh tools setup

$ ./bootstrap.sh wk configure

$ ./bootstrap.sh wk build
```

# Changes

 - Disabled bearer networking because it caused file descriptor leaks
 - Merge everything into a single repository, including the patched QT
