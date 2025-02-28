FROM debian

RUN apt-get update && apt-get install -y nginx \
    && rm -rf /var/lib/apt/lists

COPY nginx.conf /etc/nginx/nginx.conf

WORKDIR /miniserver/

RUN groupadd -g 999 dockeruser && \
    useradd -r -u 999 -g dockeruser dockeruser
USER root

ENTRYPOINT ["nginx", "-g", "daemon off;"]
