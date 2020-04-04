FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build-env

WORKDIR /orchestrus-core
ADD . .
RUN dotnet restore
RUN dotnet publish -c Release -o out


FROM mcr.microsoft.com/dotnet/core/aspnet:2.2
WORKDIR /orchestrus-core
COPY --from=build-env /orchestrus-core/out .
ENTRYPOINT ["dotnet", "aspnetcoreapp.dll"]