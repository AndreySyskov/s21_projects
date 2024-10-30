#!/bin/bash

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
curl -s --max-time 10 -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=Этап CI успешно завершен." $URL > /dev/null

curl -s --max-time 10 -d "chat_id=$TELEGRAM_USER_ID_DEN&disable_web_page_preview=1&text=Этап CI успешно завершен." $URL > /dev/null # Строка для дублирования на другой аккаунт TG
