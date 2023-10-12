docker run --privileged --cap-add=SYS_PTRACE -v $(pwd)/..:/local -it debian:bookworm /bin/bash
lldb -- /local/Wkhtmltopdf/build/app/bin/wkhtmltopdf --footer-html /local/WkBench/input/footer.html --header-html /local/WkBench/input/header.html /local/WkBench/input/ipsum-100K.html out.pdf
