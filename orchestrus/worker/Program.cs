using System;

using Docker.DotNet;

using System.Net;  
using System.Net.Sockets;  
using System.Text;  
using System.Threading;


/**

On va utiliser le SDK de docker en C# par MS
https://github.com/microsoft/Docker.DotNet

Le service de sockets est inspiré par 
https://docs.microsoft.com/fr-fr/dotnet/framework/network-programming/asynchronous-server-socket-example

**/

namespace worker
{
    class Program
    {
        static void Main(string[] args)
        {
            DockerClient client = new DockerClientConfiguration(
                new Uri("unix:///var/run/docker.sock"))
            .CreateClient();
            
            Console.WriteLine("Hello World!");
        }



        static void createContainer(DockerClient client){


        }
    }




   


        

}
