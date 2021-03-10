import java.io.*;
class s1812078k1a{
    public static void main(String args[]) throws IOException{
        int a[]={5,3,8,4,9};
        BufferedReader br=
        new BufferedReader(new InputStreamReader(System.in));
        System.out.print("新しいデータの入力 :");
        String intx=br.readLine();
        int x =Integer.parseInt(intx);
        System.out.print("新データの要素番号の入力 :");
        String intid=br.readLine();
        int id =Integer.parseInt(intid);
        //データの更新
        a[id]=x;
        //データの出力
        for (int i=0; i<5; i++) System.out.println(a[i]); 
    }
}