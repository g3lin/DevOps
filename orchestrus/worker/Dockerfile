FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster

WORKDIR /worker
ADD . .
RUN dotnet restore
CMD dotnet run 