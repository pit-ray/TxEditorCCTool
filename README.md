# TxEditorCCTool
This app allow us to convert from color setting for one text editor to it for another.

## Supported Editor
|Editor|version|
|-------|------|
|TeraPad|1.09|
|Sakura Editor|2.2.0.1|

## How to use
If you want to convert color-setting file of Sakura Editor to TeraPad, do as follows.
```shell
tecc.exe molokai.col -fr Sakura -to TeraPad -nm molokai2.tpc
````
|Options|details|
|---|---|
|-fr|assign an source editor name. `TeraPad` or `Sakura`|
|-to|assign an destination editor name. `TeraPad` or `Sakura`|
|-nm|a new file name|
