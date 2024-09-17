# git/Github チュートリアル
git/Githubを使うための情報をここに載せておきます

## 最初にすること
- gitのインストール
- git bashを開く  
ここから、このgit bashのターミナル上で作業をしていく  


## gitの初期設定
以下の内容は、[このサイト](https://prog-8.com/docs/git-env-win)に準じた内容を掲載しております。  
- ユーザーネームとメールアドレスを設定  
```
git config --global user.name "ユーザー名"
git config --global user.email "メールアドレス"
```

## GitHubにSSHの設定をする
- まず、新しいSSHキーを生成します
```
ssh-keygen -t ed25519 -C "GitHubに登録したメールアドレス"
```
- 以下のコマンドで作成できたかどうか確認できます。
```
ls ~/.ssh
```
そして、以下のように出てきたらOK
```
id_ed25519   id_ed25519.pub
```

## GithubアカウントにSSHキーを追加する
-　作成したSSHキーをアカウントに追加する。以下のコマンドで```id_ed25519.pub```に書かれた内容をコピーできる。
```
clip < ~/.ssh/id_ed25519.pub
```
- GitHubのサイトから、自分のアカウントにSSHキーを追加 [このサイト](https://prog-8.com/docs/git-env-win)参照  

- 以下のコマンドでGitHubに接続ができるか確認しよう  
```
ssh -T git@github.com
``` 

## プロジェクトをクローン
- ```nitgc_procon35_comp```というプロジェクトがあり、これを**リポジトリ**という  
今から、ここに上がっているリポジトリを自分のPCにクローンしたい。
まずは、今自分がいるフォルダを把握しておく。  
```
pwd
```
これをすることによって、自分がどのフォルダにいるかがわかる。クローンのコマンドを実行するときに、このディレクトリ下にリポジトリのフォルダができる。  
```
git clone https://github.com/nitgc-comb/nitgc_procon35_comp.git
```



