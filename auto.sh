#!/bin/bash

./Generator.py

# 获取当前时间
TIME=$(date +"%Y-%m-%d %H:%M:%S")

# 添加所有修改
git add -A

# 提交
git commit -m "Site updated: $TIME"

# 推送（如果你希望自动推送）
git push
