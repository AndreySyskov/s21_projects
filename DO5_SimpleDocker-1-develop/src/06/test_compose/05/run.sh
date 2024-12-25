#!/bin/bash

spawn-fcgi -p 8080 -f ./miniserver.out
nginx -g "daemon off;"