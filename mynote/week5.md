## 虛擬機（Virtual Machine）
狹義：
虛擬機：模擬處理器指令集的軟體
生存：模擬電腦行為的軟體
大致：
部分軟體驗模擬指令集、電腦行為，ex：VMware、VirtualPC、Virtual box
大部分的情況不會去進行邊緣，用虛擬機通稱
![p](https://github.com/zxc21949049/sp109b/blob/main/p/pw501.png)
## 測試
<pre><code>
class HelloWorld {
  public static void main(String[] args) {
     System.out.println("Hello World!");
  }
}
</code></pre>

## C4 編譯器
簡介
C4是Robert Swierczek寫的一個小型C 語言編譯器，全部 527 行的原始碼都在c4.c裡。

C4編譯完成後，會產生一種“堆疊機機器碼”放在記憶體內，然後虛擬機會立刻執行該機器碼。