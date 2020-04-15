using System; 
using System.Net;  
using System.Net.Sockets;  
using System.Text;  
using System.Collections.Generic;



namespace orchestrus_core
{
    class Program
    {
        private static string DB_IP = "bdd-controller";
        private static int DB_PORT = 4200;


        static void Main(string[] args)
        {
            Console.WriteLine("Démarrage du coeur d'orchestrus");
            bool shouldQuit = false;
            while(!shouldQuit)
                shouldQuit = parseCommand();
        }

        static bool parseCommand(){

            Console.WriteLine("Enter command (you can type \"help\"): ");
            string comm = Console.ReadLine();

            if (comm.Equals("help"))
                helpHelper();

            else if (comm.Equals("quit"))
                return true;

            else if (comm.Equals("download"))
                downloadHelper();

            else if (comm.Equals("launch"))
                launchHelper();

            else if (comm.Equals("listWorkers"))
                listWorkersHelper();

            else if (comm.Equals("addWorker"))
                addWorkerHelper();

            else if (comm.Equals("listImages"))
                listImagesHelper();

            else {
                Console.WriteLine("COMMANDE NON RECONNUE");
                Console.WriteLine("Utilisez \"help\"");
            }
            
            Console.WriteLine("\n\n");

            return false;

        }

        static void helpHelper(){
            Console.WriteLine("AIDE \n");
            Console.WriteLine("-> download    : Télécharger une image sur un worker");
            Console.WriteLine("-> launch      : Lancer une image téléchargée sur un worker");
            Console.WriteLine("-> listWorkers : Liste des workers et leur status");
            Console.WriteLine("-> addWorker   : Ajouter un worker à la base de données");
            Console.WriteLine("-> listImages  : Afficher la liste des images d'un worker: ");
        }

        static void downloadHelper(){
            Console.WriteLine("Télécharger une image sur un worker:");

            Console.WriteLine("Renseignez l'IP du runner:");
            string ip = Console.ReadLine();

            Console.WriteLine("Renseignez le port du runner:");
            int port;
            while(!Int32.TryParse(Console.ReadLine(), out port))
                Console.WriteLine("Le port doit être un chiffre");

            Console.WriteLine("Renseignez l'image à télécharger:");
            string image = Console.ReadLine();

            Console.WriteLine(dlImageOnWorkerMachine(ip,port,image));

        }

        static void launchHelper(){
            Console.WriteLine("Lancer une image téléchargée sur un worker:");

            Console.WriteLine("Renseignez l'IP du runner:");
            string ip = Console.ReadLine();

            Console.WriteLine("Renseignez le port du runner:");
            int port;
            while(!Int32.TryParse(Console.ReadLine(), out port))
                Console.WriteLine("Le port doit être un chiffre");

            Console.WriteLine("Renseignez l'image à lancer:");
            string image = Console.ReadLine();

            List<int> ports = new List<int>{};
            int portint;
            Console.WriteLine("Renseignez les ports à ouvrir:");
            string strPort ;
            bool isDone = false;
            while(!isDone){
                strPort= Console.ReadLine();
                if(string.IsNullOrEmpty(strPort))
                    isDone = true;
                else if(!Int32.TryParse(strPort, out portint))
                    Console.WriteLine("Le port doit être un chiffre");
                else
                    ports.Add(portint);
            }

            List<string> envs = new List<string>{};
            Console.WriteLine("Renseignez les varaiable d'environement:");
            string envString = Console.ReadLine();
            while(!string.IsNullOrEmpty(envString)){
                envs.Add(envString);
                envString = Console.ReadLine();
            }

            Console.WriteLine(launchOnWorkerMachine(ip,port,image,ports.ToArray(),envs.ToArray()));
            
        }

        static void listWorkersHelper(){
            Console.WriteLine("Liste des workers et leur status:");
            Console.WriteLine( listWorkerOnDB() );
            
        }

        static void addWorkerHelper(){
            Console.WriteLine("Ajouter un worker à la base de données: ");

            Console.WriteLine("Renseignez l'IP du runner:");
            string ip = Console.ReadLine();

            Console.WriteLine("Renseignez le port du runner:");
            int port;
            while(!Int32.TryParse(Console.ReadLine(), out port))
                Console.WriteLine("Le port doit être un chiffre");

            string rep = updateWorkerOnDB(ip, port, true);  
            Console.WriteLine(rep);
        }

        static void listImagesHelper(){
            Console.WriteLine("Afficher la liste des images d'un worker: ");

            Console.WriteLine("Renseignez l'IP du runner:");
            string ip = Console.ReadLine();

            Console.WriteLine("Renseignez le port du runner:");
            int port;
            while(!Int32.TryParse(Console.ReadLine(), out port))
                Console.WriteLine("Le port doit être un chiffre");


            string rep = ListImagesOnWorkerDB(ip,port);
            Console.WriteLine(rep);

        }

        static string dlImageOnWorkerMachine(string workerIP,int workerPort,string imageName){
            string JSONRequest = @"{{""request"":""imageDL"",""imageName"":""{0}""}}";
            string formattedJSONReq = String.Format(JSONRequest,imageName);
            formattedJSONReq += "\n";
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
            string JSONRequest = @"{{""request"":""imageLaunch"",""imageName"":""{0}"",""portsToOpen"":[";
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
            JSONRequest += "]}}";

            string formattedJSONReq = String.Format(JSONRequest,imageName);
            formattedJSONReq += "\n";
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


        

        static string listWorkerOnDB(){
            string JSONRequest = @"{""request"":""DBListWorkers""}";
            string formattedJSONReq = JSONRequest + "\n";
            try
            {
                string rep = sendMessage(DB_IP,DB_PORT,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi à BDDController: "+e.ToString());
            }
            return "";

        }


        static string updateWorkerOnDB(string workerIp, int workerPort, Boolean workerStatus){
            string JSONRequest = @"{{""request"":""DBUpdateWorker"",""ip"":""{0}"",""workerPort"":{1},""status"":{2} }}";
            string formattedJSONReq = String.Format(JSONRequest,workerIp,workerPort.ToString(),workerStatus.ToString().ToLower());
            formattedJSONReq += "\n";

            Console.WriteLine(formattedJSONReq);

            try
            {
                string rep = sendMessage(DB_IP,DB_PORT,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi à BDDController: "+e.ToString());
            }
            return "";

        }




        static string ListImagesOnWorkerDB(string workerIp, int workerPort){
            string JSONRequest = @"{{""request"":""DBListImages"",""ip"":""{0}"",""workerPort"":{1} }}";
            string formattedJSONReq = String.Format(JSONRequest,workerIp,workerPort);
            formattedJSONReq += "\n";
            try
            {
                string rep = sendMessage(DB_IP,DB_PORT,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi à BDDController: "+e.ToString());
            }
            return "";

        }



        static string updateImageOnDB(string workerIp, int workerPort, string IDImage, string nomImage, int[] imagePorts){
            string JSONRequest = @"{{""request"":""DBUpdateWorker"",""ip"":""{0}"",""workerPort"":{1},""idImage"":{2},""nomImage"":{3},""ImagePorts"":[";
            int i = 0;
            // Ajout des ports à ouvrir éventuels
            for (i = 0; i < imagePorts.Length; i++)
            {
                JSONRequest += imagePorts[i]+",";
            }
            if (i > 0)
                JSONRequest.Remove(JSONRequest.Length -1);
            JSONRequest += "]}}";
            string formattedJSONReq = String.Format(JSONRequest,workerIp,workerPort,IDImage, nomImage);
            formattedJSONReq += "\n";
            try
            {
                string rep = sendMessage(DB_IP,DB_PORT,formattedJSONReq);
                return rep;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans l'envoi à BDDController: "+e.ToString());
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
                    Console.WriteLine("Réponse du serveur = \"{0}\"", rep);  
    
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
