FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build-env

WORKDIR /bdd-controller
ADD . .
RUN dotnet restore
RUN dotnet publish -c Release -o out


FROM mcr.microsoft.com/dotnet/core/aspnet:3.1
WORKDIR /bdd-controller
COPY --from=build-env /bdd-controller/out .
ENTRYPOINT ["dotnet", "bdd-controller.dll"]