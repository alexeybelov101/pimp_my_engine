#pragma once
#include <iostream>
#include <getopt.h>

class ArgsParser {
public:
    struct Settings {
        double time = 60.0;         // секунды
        double frequency = 1000.0;  // Гц
        double rpm = 60.0;             //об/мин
        std::string configPath = "configs/config.json";
    };

    static Settings parse(int argc, char* argv[]) {
        Settings settings;

        static struct option long_options[] = {
            {"time",    required_argument, 0, 't'},
            {"freq",    required_argument, 0, 'f'},
            {"rpm",    required_argument, 0, 'r'},
            {"config",  required_argument, 0, 'c'},
            {"help",    no_argument,       0, 'h'},
            {0, 0, 0, 0}
        };

        int opt;
        while ((opt = getopt_long(argc, argv, "t:f:r:c:h", long_options, nullptr)) != -1) {
            switch (opt) {
                case 't':
                    settings.time = std::stod(optarg);
                    break;
                case 'f':
                    settings.frequency = std::stod(optarg);
                    break;
                case 'r':
                    settings.rpm = std::stod(optarg);
                    break;
                case 'c':
                    settings.configPath = optarg;
                    break;
                case 'h':
                    std::cout << "Usage: " << argv[0] << " [options]\n"
                            << "  -t, --time TIME      Simulation time (seconds)\n"
                            << "  -f, --freq FREQ      Simulation frequency (Hz)\n"
                            << "  -r, --rpm RPM      Engine initial RPM\n"
                            << "  -c, --config PATH    Config file path\n"
                            << "  -h, --help           Show this help\n";
                    exit(0);
                default:
                    std::cerr << "Unknown option. Use --help for usage.\n";
                    exit(1);
            }
        }

        return settings;
    }
};
