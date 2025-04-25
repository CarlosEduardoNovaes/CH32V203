#!/bin/bash

# Puxa as últimas mudanças da branch atual

BRANCH=$(git branch --show-current)
git pull origin "$BRANCH"