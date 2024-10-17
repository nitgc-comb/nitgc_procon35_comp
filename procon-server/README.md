# procon35 server
## input.json
以下のような設定ファイルを用意し, server コマンドに -c で指定して実行すると 10 秒後に試合が開始されます。
```
{
  "teams": [
    "token1",
    "token2",
    "token3"
  ],
  "duration": 300,
  "problem": {
    "board": {
      "width": 6,
      "height": 4,
      "start": [
        "220103",
        "213033",
        "022103",
        "322033"
      ],
      "goal": [
        "000000",
        "111222",
        "222233",
        "333333"
      ]
    },
    "general": {
      "n": 2,
      "patterns": [
        {
          "p": 25,
          "width": 4,
          "height": 2,
          "cells": [
            "0111",
            "1001"
          ]
        },
        {
          "p": 26,
          "width": 2,
          "height": 2,
          "cells": [
            "10",
            "01"
          ]
        }
      ]
    }
  }
}
```
`teams` にはチームのトークン情報を記述します。
`duration` には試合時間を秒で記述します。
`problem` には問題の情報を記述します。problemの形式については募集要項を参照してください。

## create testcase & start server
in directory `procon-server`, there also has test input case file and c program to create test case file

when you want to execute c program, open `Command prompt` move your current directory to `procon-server` directory and press command:
```
create_testcase
```
then, press command and setup your server:
```
procon-server_win -c {input file} -l :8080
```



## 問題情報取得
`/problem` にtokenをつけてGETリクエストを送ることで試合情報が取得できます。
試合時間内であれば設定ファイルで記述したproblemが返却されます。

```
curl -v localhost:8080/problem -H "Procon-Token: token1"
```

## 回答提出方法
`/answer` にjsonをPOSTすることで回答を送信できます。
回答の形式については募集要項を参照してください。
```json
{
  "n":3,
  "ops":[
    {
      "p":4,
      "x":1,
      "y":1,
      "s":2
    },
    {
      "p":11,
      "x":3,
      "y":-12,
      "s":3
    },
    {
      "p":25,
      "x":3,
      "y":3,
      "s":0
    }
  ]
}
```
回答が受理されるとrevisionという回答を受け付けた番号が返却されます。
```
curl -X POST -H "Content-Type: application/json" -H "Procon-Token: token1" localhost:8080/answer -d @solution.json
```


