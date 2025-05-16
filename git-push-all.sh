#!/bin/bash

# Faz add de todos os arquivos, commit com mensagem fornecida e push

echo "Mensagem do commit:"
read -p "Mensagem de commit: " mensagem
#mensagem="comit"

git status
git add .
git commit -m "$mensagem"
BRANCH=$(git branch --show-current)
git push origin "$BRANCH"
