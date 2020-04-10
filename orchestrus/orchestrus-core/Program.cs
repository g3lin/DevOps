using System; 
using System.Net;  
using System.Net.Sockets;  
using System.Text;  


namespace orchestrus_core
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Démarrage du coeur d'orchestrus");
            sendMessage("worker",4242,"TEST\nseconde ligne\n\n");
        }

        static string dlImageOnWorkerMachine(string workerIP,int workerPort,string imageName){
            string JSONRequest = @"{""request"":""imageDL"",""imageName"":""{0}""}";
            string formattedJSONReq = String.Format(JSONRequest,imageName);
            formattedJSONReq += "\n\n";
            try
            {
                string rep = sendMessage(workerIP,workerPort,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi: "+e.ToString());
            }
            return "";
        }



        static string launchOnWorkerMachine(string workerIP,int workerPort,string imageName, int[] ports, string[] envs){
            string JSONRequest = @"{""request"":""imageLaunch"",""imageName"":""{0}"",""portsToOpen"":[";
            int i = 0;
            // Ajout des ports à ouvrir éventuels
            for (i = 0; i < ports.Length; i++)
            {
                JSONRequest += ports[i]+",";
            }
            if (i > 0)
                JSONRequest.Remove(JSONRequest.Length -1);

            // Ajout des variables d'env eventuelles
            i = 0;
            for (i = 0; i < envs.Length; i++)
            {
                JSONRequest += envs[i]+",";
            }
            if (i > 0)
                JSONRequest.Remove(JSONRequest.Length -1);
            JSONRequest += "]}";

            string formattedJSONReq = String.Format(JSONRequest,imageName);
            formattedJSONReq += "\n\n";
            try
            {
                string rep = sendMessage(workerIP,workerPort,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi: "+e.ToString());
            }
            return "";

        }


        



        static string sendMessage(string IPAddress, int port, string message){
            
        // Data buffer for incoming data.  
            byte[] bytes = new byte[1024];  
    
            // Connect to a remote device.  
            try { 
                IPHostEntry ipHostInfo; 
                // Establish the remote endpoint for the socket.  
                if(IPAddress.Equals("localhost"))
                    ipHostInfo = Dns.GetHostEntry(Dns.GetHostName()); 
                
                else
                    ipHostInfo = Dns.GetHostEntry(IPAddress);

                
                IPAddress ipAddress = ipHostInfo.AddressList[0];  
                IPEndPoint remoteEP = new IPEndPoint(ipAddress,port);  
    
                // Create a TCP/IP  socket.  
                Socket sender = new Socket(ipAddress.AddressFamily,
                    SocketType.Stream, ProtocolType.Tcp );  
    
                // Connect the socket to the remote endpoint. Catch any errors.  
                try {  
                    sender.Connect(remoteEP);  
    
                    Console.WriteLine("Socket connected to {0}",  
                        sender.RemoteEndPoint.ToString());  
    
                    // Encode the data string into a byte array.  
                    byte[] msg = Encoding.ASCII.GetBytes(message);  
    
                    // Send the data through the socket.  
                    int bytesSent = sender.Send(msg);  
    
                    // Receive the response from the remote device.  
                    int bytesRec = sender.Receive(bytes);  
                    string rep = Encoding.ASCII.GetString(bytes,0,bytesRec);
                    Console.WriteLine("Echoed test = {0}", rep);  
    
                    // Release the socket.  
                    sender.Shutdown(SocketShutdown.Both);  
                    sender.Close();

                    return rep;  
    
                } catch (ArgumentNullException ane) {  
                    Console.WriteLine("ArgumentNullException : {0}",ane.ToString());  
                } catch (SocketException se) {  
                    Console.WriteLine("SocketException : {0}",se.ToString());  
                } catch (Exception e) {  
                    Console.WriteLine("Unexpected exception : {0}", e.ToString());  
                }  
    
            } catch (Exception e) {  
                Console.WriteLine( e.ToString());  
            }  

            return "";
        }  
  
    }   

}
