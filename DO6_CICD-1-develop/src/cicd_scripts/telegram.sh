#!/bin/bash

#TELEGRAM_BOT_TOKEN="7074280816:AAF7qmMXD2loiVPtpJSRgoFD2ieq8FJ4O08"
#TELEGRAM_USER_ID="139577662"
TIME=10


URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Commit: $CI_COMMIT_SHA%0A%0A Message: $CI_COMMIT_MESSAGE%0A%0A $CI_JOB_NAME status: $CI_JOB_STATUS$1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG %0A$ID_PEER"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID_DEN&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null # Строка для дублирования на другой аккаунт TG