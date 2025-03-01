FROM debian

#USER root

RUN apt-get update && apt-get install -y \
nginx \
gcc \
libfcgi-dev \
spawn-fcgi && rm -rf /var/lib/apt/lists


COPY miniserver.c ./miniserver/miniserver.c
COPY nginx.conf etc/nginx/nginx.conf
COPY run.sh ./miniserver/run.sh

WORKDIR /miniserver/

RUN gcc -c miniserver.c -o miniserver.o \
&& gcc miniserver.o -lfcgi -o miniserver.out \
&& chmod +x run.sh
RUN groupadd -g 999 dockeruser && \
    useradd -r -u 999 -g dockeruser dockeruser 
   # echo "dockeruser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER dockeruser

CMD ["./run.sh" ]