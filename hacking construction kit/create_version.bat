@echo off

SET VERSION_FILE=version.h
SET COUNT_FILE=count.h

SET LINE=
SET PRODUCT_VERSION=
IF NOT EXIST %COUNT_FILE%  ECHO 0 > %COUNT_FILE%
FOR /f %%a IN (%COUNT_FILE%) DO (
	SET LINE=%%a
	GOTO BREAK_FOR
)
:BREAK_FOR
SET /a VERSION=%LINE%+1

ECHO %VERSION% > %COUNT_FILE%

ECHO #pragma once > %VERSION_FILE%
ECHO #define VERSION %version% > %VERSION_FILE%

