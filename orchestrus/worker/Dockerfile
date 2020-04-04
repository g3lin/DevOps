FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build-env

WORKDIR /worker
ADD . .
RUN dotnet restore
RUN dotnet publish -c Release -o out


FROM mcr.microsoft.com/dotnet/core/aspnet:3.1
WORKDIR /worker
COPY --from=build-env /worker/out .
ENTRYPOINT ["dotnet", "worker.dll"]