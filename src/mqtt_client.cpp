#include <iostream>
#include "mqtt/client.h"

const std::string ADDRESS = "ssl://a24dapxtisvrk0-ats.iot.ap-south-1.amazonaws.com:8883";
const std::string CLIENT_ID = "basicPubSub";
const std::string TOPIC = "sdk/test/python";

const std::string PATH_TO_CA = "../root-CA.crt";
const std::string PATH_TO_CERT = "../Demo_MQTT.cert.pem";
const std::string PATH_TO_KEY = "../Demo_MQTT.private.key";

int main(int argc, char* argv[]) {
    mqtt::ssl_options sslopts;
    sslopts.set_trust_store(PATH_TO_CA);
    sslopts.set_key_store(PATH_TO_CERT);
    sslopts.set_private_key(PATH_TO_KEY);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
    connOpts.set_ssl(sslopts);

    mqtt::client client(ADDRESS, CLIENT_ID);

    try {
        std::cout << "Connecting to the MQTT server..." << std::flush;
        client.connect(connOpts);
        std::cout << "Connected\n";

        std::cout << "Publishing message..." << std::flush;
        // Create a message object
        mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, "Hello from MQTT!", 1, false);
        client.publish(pubmsg);
        std::cout << "Message published\n";

        client.disconnect();
        std::cout << "Disconnected" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "An error occurred: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}