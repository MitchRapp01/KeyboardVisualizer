#include "KeyboardVisDlg.h"
#include <QApplication>
#include "KeyboardVisualizerCommon/Visualizer.h"
#include "KeyboardVisualizerCommon/VisualizerDefines.h"

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

Visualizer vis;
static boolean startminimized;

void parse_argument_string(char * argument, char * value)
{
    if (strcmp(argument, "startminimized") == 0)
    {
        startminimized = true;
    }

    if (strcmp(argument, "amplitude") == 0)
    {
        vis.amplitude = atoi(value);
    }

    if (strcmp(argument, "bkgd_bright") == 0)
    {
        vis.bkgd_bright = atoi(value);
    }

    if (strcmp(argument, "avg_size") == 0)
    {
        vis.avg_size = atoi(value);
        if (vis.avg_size < 1)
        {
            vis.avg_size = 1;
        }
        else if (vis.avg_size > 128)
        {
            vis.avg_size = 128;
        }
    }

    if (strcmp(argument, "decay") == 0)
    {
        vis.decay = atoi(value);
    }

    if (strcmp(argument, "delay") == 0)
    {
        vis.delay = atoi(value);
    }

    if (strcmp(argument, "nrml_ofst") == 0)
    {
        vis.nrml_ofst = strtod(value, NULL);
    }

    if (strcmp(argument, "nrml_scl") == 0)
    {
        vis.nrml_scl = strtod(value, NULL);
    }

    if (strcmp(argument, "anim_speed") == 0)
    {
        vis.anim_speed = strtod(value, NULL);
    }

    if (strcmp(argument, "window_mode") == 0)
    {
        if ((atoi(value) >= 0) && (atoi(value) <= 4))
        {
            vis.window_mode = atoi(value);
        }
    }

    if (strcmp(argument, "bkgd_mode") == 0)
    {
        if ((atoi(value) >= 0) && (atoi(value) <= VISUALIZER_NUM_PATTERNS))
        {
            vis.bkgd_mode = atoi(value);
        }
    }

    if (strcmp(argument, "frgd_mode") == 0)
    {
        if ((atoi(value) >= 0) && (atoi(value) <= VISUALIZER_NUM_PATTERNS))
        {
            vis.frgd_mode = atoi(value);
        }
    }

    if (strcmp(argument, "single_color_mode") == 0)
    {
        if ((atoi(value) >= 0) && (atoi(value) <= VISUALIZER_NUM_SINGLE_COLOR))
        {
            vis.single_color_mode = atoi(value);
        }
    }

    if (strcmp(argument, "avg_mode") == 0)
    {
        if ((atoi(value) >= 0) && (atoi(value) <= 1))
        {
            vis.avg_mode = atoi(value);
        }
    }

    if (strcmp(argument, "ledstrip") == 0)
    {
        vis.AddLEDStrip(value);
    }

    if (strcmp(argument, "xmas") == 0)
    {
        vis.AddLEDStripXmas(value);
    }

    if (strcmp(argument, "server") == 0)
    {
        vis.InitServer(value);
    }

    if (strcmp(argument, "client") == 0)
    {
        vis.InitClient(value);
    }
}

bool parse_command_line(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        char* argument;
        char* value;

        argument = strtok_r(argv[i], "=", &value);

        if (strcmp(argument, "help") == 0)
        {
            printf("\r\n");
            printf("Available command line commands:\r\n");
            printf("    help              - Display this message and quit\r\n");
            //printf("    nogui             - Run visualizer with no GUI\r\n");
            printf("    startminimized    - Start in system tray\r\n");
            printf("\r\n");
            printf("Available command line arguments:\r\n");
            printf("    Usage: argument1=value1 argument2=value2 ...\r\n");
            printf("\r\n");
            printf("    amplitude         - Adjust the amplitude of the visualizer\r\n");
            printf("    bkgd_bright       - Adjust the background brightness\r\n");
            printf("    avg_size          - Number of points to average\r\n");
            printf("    decay             - Percentage of value to decay every step\r\n");
            printf("    delay             - Milliseconds between each device update\r\n");
            printf("    nrml_ofst         - Normalization offset, floating point value\r\n");
            printf("    nrml_scl          - Normalization scale, floating point value\r\n");
            printf("    window_mode       - FFT windowing mode selector, values are:\r\n");
            printf("                      - 0:  No windowing\r\n");
            printf("                      - 1:  Hanning window\r\n");
            printf("                      - 2:  Hamming window\r\n");
            printf("                      - 3:  Blackman window\r\n");
            printf("    bkgd_mode         - Background mode, values are:\r\n");
            for (int i = 0; i < VISUALIZER_NUM_PATTERNS; i++)
            {
                if (i < 10)
                {
                    printf("                      - %d  %s\r\n", i, visualizer_pattern_labels[i]);
                }
                else
                {
                    printf("                      - %d %s\r\n", i, visualizer_pattern_labels[i]);
                }
            }
            printf("    frgd_mode         - Foreground mode, values are:\r\n");
            for (int i = 0; i < VISUALIZER_NUM_PATTERNS; i++)
            {
                if (i < 10)
                {
                    printf("                      - %d  %s\r\n", i, visualizer_pattern_labels[i]);
                }
                else
                {
                    printf("                      - %d %s\r\n", i, visualizer_pattern_labels[i]);
                }
            }
            printf("    single_color_mode - Single color mode, values are:\r\n");
            for (int i = 0; i < VISUALIZER_NUM_SINGLE_COLOR; i++)
            {
                if (i < 10)
                {
                    printf("                      - %d  %s\r\n", i, visualizer_single_color_labels[i]);
                }
                else
                {
                    printf("                      - %d %s\r\n", i, visualizer_single_color_labels[i]);
                }
            }
            printf("    avg_mode          - Visualizer averaging mode\r\n");
            printf("                      - 0:  Binning\r\n");
            printf("                      - 1:  Low-pass filtering\r\n");
            printf("    anim_speed        - Animation Speed (percent)\r\n");
            printf("    server            - Configure this instance as a server for synchronization\r\n");
            printf("                      -  Takes what port to serve on as argument, i.e. server=1234\r\n");
            printf("    client            - Configure this instance as a client for synchronization\r\n");
            printf("                      -  Takes the IP/hostname of the server and port as arguments,\r\n");
            printf("                      -  i.e. client=192.168.1.100,1234\r\n");
            printf("    ledstrip          - LED config strings :\r\n");
            printf("                      - Serial : ledstrip = port, baud, num_leds\r\n");
            printf("                      - (ex.ledstrip = COM1, 115200, 30)\r\n");
            printf("                      - UDP : ledstrip = client, port, num_leds\r\n");
            printf("                      - (ex.ledstrip = 192.168.1.5, 1234, 30)\r\n");
            printf("    xmas              - COM port, ex. xmas=COM2\r\n");
            return false;
        }

        parse_argument_string(argument, value);
    }
    return true;
}

void parse_settings_file(char * filename)
{
    std::ifstream infile;

    //Open settings file
    infile.open(filename);

    if (infile.good())
    {
        for (std::string line; std::getline(infile, line); )
        {
            if (line == "")
            {
                continue;
            }
            if ((line[0] != ';') && (line[0] != '#') && (line[0] != '/'))
            {
                char * argument;
                char * value;

                value = (char *)line.c_str();

                argument = strtok_r(value, "=", &value);

                parse_argument_string(argument, value);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    startminimized = false;

    //Initialize Visualizer
    vis.Initialize();

    //Get file path in executable directory
    char filename[2048];
    //GetModuleFileName(NULL, filename, 2048);
    char arg1[64];
    snprintf(arg1, 64, "/proc/%d/exe", getpid());
    readlink(arg1, filename, 1024);
    strcpy(filename, std::string(filename).substr(0, std::string(filename).find_last_of("\\/")).c_str());
    //strcat(filename, "\\settings.txt");
    strcat(filename, "/settings.txt");
    parse_settings_file(filename);

    //Parse Command Line
    if (!parse_command_line(argc, argv))
    {
        return 0;
    }

    //Start Visualizer Threads
    vis.StartThread();

    //Create Dialog
    Ui::KeyboardVisDlg dlg;
    dlg.StartMinimized(startminimized);
    dlg.SetVisualizer(&vis);
    dlg.show();

    return a.exec();
}
