FROM maven:3.8-openjdk-17 AS build
WORKDIR /app
COPY . .
#RUN mvn clean package

#FROM openjdk:17-jdk-slim
#COPY --from=build /app/target/my-app.jar /app/my-app.jar
#CMD ["java", "-jar", "/app/my-app.jar"]