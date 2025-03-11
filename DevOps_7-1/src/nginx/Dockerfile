FROM nginx:1.25.5-alpine

COPY nginx.conf /etc/nginx/nginx.conf

WORKDIR /miniserver/

USER root

ENTRYPOINT ["nginx", "-g", "daemon off;"]
