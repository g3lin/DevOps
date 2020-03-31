using System;

using Docker.DotNet;
using Docker.DotNet.Models;

using System.Net;  
using System.Net.Sockets;  
using System.Text;  
using System.Threading.Tasks;
using System.Threading;

using System.IO;


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
        static async Task Main(string[] args)
        {
            DockerClient client = new DockerClientConfiguration(
                new Uri("unix:///var/run/docker.sock"))
            .CreateClient();

            Task.Run(async () =>
            {
                await client.Images.CreateImageAsync(
                new ImagesCreateParameters
                {
                    FromImage = "alpine",
                    Tag = "3.11.5",
                },
                 new AuthConfig(), new Progress<JSONMessage>(), CancellationToken.None);


            }).GetAwaiter().GetResult();

            

            
            
            // Console.WriteLine("Hello World!");
        }



        static async void createContainer(DockerClient client){
                        
        }
    }




   


        

}
