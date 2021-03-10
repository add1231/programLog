<?php
    session_start();
    /*print_r($_SESSION);
    print_r($_COOKIE);*/
    $login=0;
    $username =null;
    $stmh=null;
    $serachresult =null;
    $_SESSION['success']=0;
    try{
        $pdo = new PDO('mysql:host=localhost;dbname=wa2;charset=utf8','','');
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $pdo->setAttribute(PDO::ATTR_EMULATE_PREPARES,false);
    
        //ここでデータベースの処理を行います。
        if (isset($_REQUEST["login"])) {
            // 1. ユーザIDの入力チェック
            if (empty($_REQUEST["username"])) {  // emptyは値が空のとき
                echo 'ユーザーIDが未入力です。';
            } else if (empty($_REQUEST["password"])) {
                echo 'パスワードが未入力です。';
            }
        }
        if(isset($_REQUEST["username"])){
            $username = $_REQUEST["username"];
            $password = $_REQUEST["password"];
            $sql = "SELECT * FROM s1812078_kadaifinalusers WHERE username=:username;";
            $stmh = $pdo->prepare($sql);
            $stmh->bindValue(':username',$username);
            $stmh->execute();
            $login++;
            foreach($stmh as $serachresult) {
                if($username===$serachresult['username']){
                    $login++;
                }else {
                    print("<p>ユーザー名が違います</p>");
                }
                if($password===$serachresult['password']){
                    $login++;
                }else {
                    print("<p>パスワードが違います</p>");
                }
            }
        }
        if($login===1){
            print("<p>ユーザー名が違います</p>");
        }
        if($login===3){
            $_SESSION["success"] = 1;
            }
        if(!isset($_SESSION["success"])) {
            $_SESSION["success"] =0;
            } 
        if(isset($_REQUEST["touroku"])){
            // 1. ユーザIDの入力チェック
            if (empty($_REQUEST["newusername"])) {  // emptyは値が空のとき
                echo 'ユーザーIDが未入力です。';
            } else if (empty($_REQUEST["newpassword"])) {
                echo 'パスワードが未入力です。';
            } else {
                $newusername = $_REQUEST["newusername"];
                $newpassword = $_REQUEST["newpassword"];
                $sql = "INSERT INTO s1812078_kadaifinalusers(username, password) VALUES(:newusername,:newpassword);";
                $stmh = $pdo->prepare($sql);
                $stmh->bindValue(':newusername',$newusername);
                $stmh->bindValue(':newpassword',$newpassword);
                $stmh->execute();

            }
        }
        $pdo = null; //インスタンスの破棄、データベースへの接続切断
    }catch(PDOException $exception){
        die('接続エラー:'. $exception->getMessage());
    }
    
?>
<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" type="text/css" href="final.css">
    <title>kadaifinal</title>
</head>
<body>
    <h1>タスクマネージャーVer.1</h1>
    <p class=text>タスク管理を行うWebアプリケーションです。アカウントをお持ちの方はログインを、新規登録の方は下記フォームから登録を行ってください</p>
    <div class=login>
    <?php if($_SESSION["success"]===0) { ?>
        <form action="kadaifinal.php" method="post">
        <p>既にアカウントを持っている場合</p>
        <p>ユーザー名:<input type="text" name="username"></p>
        <p>パスワード:<input type="password" name="password"></p>
        <input type="submit" value="ログイン" name="login">
        </form>
        <form action="kadaifinal.php" method="post">
        <p>新規登録の場合</p>
        <p>ユーザー名:<input type="text" name="newusername"></p>
        <p>パスワード:<input type="password" name="newpassword"></p>
        <input type="submit" value="登録" name="touroku" onclick="alert('アカウントを作成しました。指定のフォームからログインしてください。');">
        </form>
    <?php } else {
        $_SESSION['username'] = $username;
        header("Location:main.php");
        }
    ?>
    </div>
    <p></p>
</body>
</html>