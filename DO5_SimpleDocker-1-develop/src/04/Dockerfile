FROM nginx

USER root

RUN apt-get update && apt-get install -y \
    gcc \
    libfcgi-dev \
    spawn-fcgi

COPY ./miniserver.c ./miniserver/miniserver.c
COPY ./nginx.conf etc/nginx/nginx.conf
COPY run.sh ./miniserver/run.sh

WORKDIR /miniserver/

RUN gcc -c /miniserver/miniserver.c -o miniserver.o \
    && gcc miniserver.o -lfcgi -o miniserver.out \
    && chmod +x run.sh

CMD ["/miniserver/run.sh"]