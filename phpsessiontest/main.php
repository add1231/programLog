<?php
    session_start();    
    $username = $_SESSION['username'];
    $pdo = new PDO('mysql:host=localhost;dbname=wa2;charset=utf8','','');
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $pdo->setAttribute(PDO::ATTR_EMULATE_PREPARES,false);
    if (isset($_REQUEST["create"])) {
        $title = $_REQUEST["title"];
        $main = $_REQUEST["main"];
        $limittime = $_REQUEST["limittime"];
        $sql = "INSERT INTO s1812078_kadaifinal(username, title, main, limittime) VALUES(:username,:title,:main,:limittime);";
        $stmh = $pdo->prepare($sql);
        $stmh->bindValue(':username',$username);
        $stmh->bindValue(':title',$title);
        $stmh->bindValue(':main',$main);
        $stmh->bindValue(':limittime',$limittime);
        $stmh->execute();
    }
    if(isset($_REQUEST["delete"])){
        $delete = $_REQUEST["dtitle"];
        $sql ="DELETE from s1812078_kadaifinal where title = :dtitle";
        $stmh = $pdo->prepare($sql);
        $stmh->bindValue(':dtitle',$delete);
        $stmh->execute();
    }
    ?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" type="text/css" href="final.css">
    <title>main</title>
</head>
<body>
    <?php
        echo("<p> ようこそ". $_SESSION['username'] ."さん </p>");
        ?>
    <h1>タスクマネージャーVer.1</h1>
    <div class=create>
        <form action="main.php" method="post">
            <p>新規タスク登録</p>
            <p>タイトル:<input type="text" name="title"></p>
            <p>内容:</p><textarea name="main" cols="30" rows="10"></textarea>
            <p>タスクの期限:<input type="date" name="limittime"></p>
            <input type="submit" value="登録" name="create" onclick="alert('タスクを作成しました');">
        </form>
    </div>
    <div class=delete>
        <form action="main.php" method="post">
            <p>タスク削除</p>
            <p>削除したいタスクのタイトル:<input type="text" name="dtitle"></p>
            <input type="submit" value="削除" name="delete" onclick="alert('タスクを削除しました');">
        </form>
    </div>
    <?php
        $sql = "SELECT * FROM s1812078_kadaifinal WHERE username=:username ORDER BY limittime;";
        $stmh = $pdo->prepare($sql);
        $stmh->bindValue(':username',$username);
        $stmh->execute();

        foreach($stmh as $row){
            echo('<div class=task>');
            echo('<p>タスク名：' . $row['title'] . '</p>');
            echo('<p>内容：' . $row['main'] . '</p>');
            echo('<p>期限：' . $row['limittime'] . '</p>');
            echo('</div>');
        }
    ?>
</body>
</html>