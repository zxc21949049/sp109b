using System;
using System.IO;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
namespace Crawler
{
    class Program
    {
        static void Main(string[] args)
        {
            string url = "https://www.lmmpic.com/139232.html?fbclid=IwAR2rORzenRSuuV8pkirobRHL1Xd_rXe5H1lWgImO244rZz4JFCuR9nFcCTo";
            string path = @"C:\Users\USER\sp109b\";
            HttpWebRequest webRequest = WebRequest.CreateHttp(url);
            webRequest.Method = "GET";
            webRequest.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) ";
            var webResponse = webRequest.GetResponse();
            StreamReader streamReader = new StreamReader(webResponse.GetResponseStream(), Encoding.UTF8);
            string str = streamReader.ReadToEnd();
            streamReader.Close();
            if (string.IsNullOrEmpty(str))
            {
                Console.WriteLine("————————-错误—————————");
                Console.ReadKey();
            }
            Regex regex = new Regex("<img.*?src=['|\"](?<Collect>(.*?(?:\\.(?:png|jpg|gif))))['|\"]");
            MatchCollection match = regex.Matches(str);
            WebClient client = new WebClient();
            int name = 0;
            try
            {
                foreach (Match match1 in match)
                {
                    string src = match1.Groups["Collect"].Value;
                    src = "http:"+src;
                    name++;
                    client.DownloadFile(src,path+name+".jpg");
                    Console.WriteLine("\n正在爬取———————" + "|" +src);                  
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("-------------" + ex);
            }
            Console.ReadKey();
        }

    }
}
————————————————
版权声明：本文为CSDN博主「xgq_Star」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
链接：https://blog.csdn.net/xgq_Star/article/details/106024418