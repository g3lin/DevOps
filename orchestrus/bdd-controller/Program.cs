using System;
using System.Threading.Tasks;
using Npgsql;

namespace bdd_controller
{
    class Program
    {
        static async Task Main(string[] args)
        {
            string pgPassword = Environment.GetEnvironmentVariable("POSTGRES_PASSWORD");
            var connString = "Host=postgres;Username=postgres;Password="+pgPassword+";Database=IGL601";

            await using var conn = new NpgsqlConnection(connString);
            await conn.OpenAsync();

            // Insert some data
            await using (var cmd = new NpgsqlCommand("INSERT INTO data (some_field) VALUES (@p)", conn))
            {
                cmd.Parameters.AddWithValue("p", "Hello world");
                await cmd.ExecuteNonQueryAsync();
            }

            // Retrieve all rows
            await using (var cmd = new NpgsqlCommand("SELECT some_field FROM data", conn))
            await using (var reader = await cmd.ExecuteReaderAsync())
                while (await reader.ReadAsync())
                    Console.WriteLine(reader.GetString(0));
        }


        public static string parseCommand(string content){
            string rep = "";

            return rep;
        }

    }
}
