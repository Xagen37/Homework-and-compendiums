import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.6.10"
    application
    antlr
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
    antlr("org.antlr:antlr4:4.9.3")
}

tasks.test {
    useJUnitPlatform()
}

tasks.generateGrammarSource {
    arguments = arguments + listOf("-no-visitor", "-no-listener", "-long-messages")
}

tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"

    dependsOn(tasks.generateGrammarSource)
}

application {
    mainClass.set("MainKt")
}