//
// Created by hadar on 12/26/19.
//

#ifndef FLIGHTSIMULATOR_SYMBOLTABLE_H
#define FLIGHTSIMULATOR_SYMBOLTABLE_H

#include <string>
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include "ex1.h"
#include "unordered_map"


class SymbolTable {
    //Variable * t = new Variable();
    unordered_map<string, Variable *> map;

//        map <string, Variable*> mapa = {
//            {"airspeed-indicator_indicated-speed-kt" , new Variable()},
//            {"time_warp" , new Variable()},
//            {"switches_magnetos" , new Variable()},
//            {"heading-indicator_offset-deg" , new Variable()},
//            {"altimeter_indicated-altitude-ft" , new Variable()},
//            {"altimeter_pressure-alt-ft" , new Variable()},
//            {"attitude-indicator_indicated-pitch-deg" , new Variable()},
//            {"attitude-indicator_indicated-roll-deg" , new Variable()},
//            {"attitude-indicator_internal-pitch-deg" , new Variable()},
//            {"attitude-indicator_internal-roll-deg" , new Variable()},
//            {"encoder_indicated-altitude-ft" , new Variable()},
//            {"encoder_pressure-alt-ft" , new Variable()},
//            {"gps_indicated-altitude-ft" , new Variable()},
//            {"gps_indicated-ground-speed-kt" , new Variable()},
//            {"gps_indicated-vertical-speed" , new Variable()},
//            {"indicated-heading-deg" , new Variable()},
//            {"magnetic-compass_indicated-heading-deg" , new Variable()},
//            {"slip-skid-ball_indicated-slip-skid" , new Variable()},
//            {"turn-indicator_indicated-turn-rate" , new Variable()},
//            {"vertical-speed-indicator_indicated-speed-fpm" , new Variable()},
//            {"flight_aileron" , new Variable()},
//            {"flight_elevator" , new Variable()},
//            {"flight_rudder" , new Variable()},
//            {"flight_flaps" , new Variable()},
//            {"engine_throttle" , new Variable()},
//            {"current-engine_throttle" , new Variable()},
//            {"switches_master-avionics" , new Variable()},
//            {"switches_starter" , new Variable()},
//            {"active-engine_auto-start" , new Variable()},
//            {"flight_speedbrake" , new Variable()},
//            {"c172p_brake-parking" , new Variable()},
//            {"engine_primer" , new Variable()},
//            {"current-engine_mixture" , new Variable()},
//            {"switches_master-bat" , new Variable()},
//            {"switches_master-alt" , new Variable()},
//            {"engine_rpm" , new Variable()}
//    };
    unordered_map<string, string> symbolMap = { // sim name to to sim val- in var
            {"airspeed-indicator_indicated-speed-kt",        "/instrumentation/airspeed-indicator/indicated-speed-kt"},
            {"time_warp",                                    "/sim/time/warp"},
            {"switches_magnetos",                            "controls/switches/magnetos"},
            {"heading-indicator_offset-deg",                 "instrumentation/heading-indicator/offset-deg"},
            {"altimeter_indicated-altitude-ft",              "instrumentation/altimeter/indicated-altitude-ft"},
            {"altimeter_pressure-alt-ft",                    "instrumentation/altimeter/pressure-alt-ft"},
            {"attitude-indicator_indicated-pitch-deg",       "instrumentation/attitude-indicator/indicated-pitch-deg"},
            {"attitude-indicator_indicated-roll-deg",        "instrumentation/attitude-indicator/indicated-roll-deg"},
            {"attitude-indicator_internal-pitch-deg",        "instrumentation/attitude-indicator/internal-pitch-deg"},
            {"attitude-indicator_internal-roll-deg",         "instrumentation/attitude-indicator/internal-roll-deg"},
            {"encoder_indicated-altitude-ft",                "instrumentation/encoder/indicated-altitude-ft"},
            {"encoder_pressure-alt-ft",                      "instrumentation/encoder/pressure-alt-ft"},
            {"gps_indicated-altitude-ft",                    "instrumentation/gps/indicated-altitude-ft"},
            {"gps_indicated-ground-speed-kt",                "instrumentation/gps/indicated-ground-speed-kt"},
            {"gps_indicated-vertical-speed",                 "instrumentation/gps/indicated-vertical-speed"},
            {"indicated-heading-deg",                        "instrumentation/heading-indicator/indicated-heading-deg"},
            {"magnetic-compass_indicated-heading-deg",       "instrumentation/magnetic-compass/indicated-heading-deg"},
            {"slip-skid-ball_indicated-slip-skid",           "instrumentation/slip-skid-ball/indicated-slip-skid"},
            {"turn-indicator_indicated-turn-rate",           "instrumentation/turn-indicator/indicated-turn-rate"},
            {"vertical-speed-indicator_indicated-speed-fpm", "instrumentation/vertical-speed-indicator/indicated-speed-fpm"},
            {"flight_aileron",                               "controls/flight/aileron"},
            {"flight_elevator",                              "controls/flight/elevator"},
            {"flight_rudder",                                "controls/flight/rudder"},
            {"flight_flaps",                                 "controls/flight/flaps"},
            {"engine_throttle",                              "controls/engines/engine/throttle"},
            {"current-engine_throttle",                      "controls/engines/current-engine/throttle"},
            {"switches_master-avionics",                     "controls/switches/master-avionics"},
            {"switches_starter",                             "controls/switches/starter"},
            {"active-engine_auto-start",                     "engines/active-engine/auto-start"},
            {"flight_speedbrake",                            "controls/flight/speedbrake"},
            {"c172p_brake-parking",                          "sim/model/c172p/brake-parking"},
            {"engine_primer",                                "controls/engines/engine/primer"},
            {"current-engine_mixture",                       "controls/engines/current-engine/mixture"},
            {"switches_master-bat",                          "controls/switches/master-bat"},
            {"switches_master-alt",                          "controls/switches/master-alt"},
            {"engine_rpm",                                   "engines/engine/rpm"}
    };
//    unordered_map <string, string> simToVal = { // sim path to client name
//            {"/instrumentation/airspeed-indicator/indicated-speed-kt", "airspeed"},
//            {"/sim/time/warp","warp"},
//            {"controls/switches/magnetos","magnetos"},
//            {"instrumentation/heading-indicator/offset-deg",""},
//            {"instrumentation/altimeter/indicated-altitude-ft","alt"}, //
//            {"instrumentation/altimeter/pressure-alt-ft",""},
//            {"instrumentation/attitude-indicator/indicated-pitch-deg",""},
//            {"instrumentation/attitude-indicator/indicated-roll-deg",""},
//            {"instrumentation/attitude-indicator/internal-pitch-deg",""},
//            {"instrumentation/attitude-indicator/internal-roll-deg",""},
//            {"instrumentation/encoder/indicated-altitude-ft",""},
//            {"instrumentation/encoder/pressure-alt-ft",""},
//            {"instrumentation/gps/indicated-altitude-ft",""},
//            {"instrumentation/gps/indicated-ground-speed-kt",""},
//            {"instrumentation/gps/indicated-vertical-speed",""},
//            {"instrumentation/heading-indicator/indicated-heading-deg",""},
//            {"instrumentation/magnetic-compass/indicated-heading-deg",""},
//            {"instrumentation/slip-skid-ball/indicated-slip-skid",""},
//            {"instrumentation/turn-indicator/indicated-turn-rate",""},
//            {"instrumentation/vertical-speed-indicator/indicated-speed-fpm",""},
//            {"controls/flight/aileron","aileron"}, //
//            {"controls/flight/elevator","elevator"}, //
//            {"controls/flight/rudder",""},
//            {"controls/flight/flaps",""},
//            {"controls/engines/engine/throttle",""},
//            {"controls/engines/current-engine/throttle","throttle"}, //
//            {"controls/switches/master-avionics",""},
//            {"controls/switches/starter",""},
//            {"engines/active-engine/auto-start",""},
//            {"controls/flight/speedbrake",""},
//            {"sim/model/c172p/brake-parking",""},
//            {"controls/engines/engine/primer",""},
//            {"controls/engines/current-engine/mixture",""},
//            {"controls/switches/master-bat",""},
//            {"controls/switches/master-alt",""},
//            {"engines/engine/rpm","rpm"} //
//    };

//unordered_map <string, Variable*> map;

    void insertToMap(unordered_map<string, Variable *> map) {
        Variable *airspeed_indicator_indicated_speed_kt = new Variable(
                "/instrumentation/airspeed-indicator/indicated-speed-kt");
        map["airspeed_indicator_indicated_speed_kt"] = airspeed_indicator_indicated_speed_kt;
        Variable *time_warp = new Variable("/sim/time/warp");
        map["time_warp"] = time_warp;
        Variable *switches_magnetos = new Variable("/controls/switches/magnetos");
        map["switches_magnetos"] = switches_magnetos;
        Variable *heading_indicator_offset_deg = new Variable("/instrumentation/heading-indicator/offset-deg");
        map["heading_indicator_offset_deg"] = heading_indicator_offset_deg;
        Variable *altimeter_indicated_altitude_ft = new Variable("/instrumentation/altimeter/indicated-altitude-ft");
        map["altimeter_indicated_altitude_ft"] = altimeter_indicated_altitude_ft;
        Variable *altimeter_pressure_alt_ft = new Variable("/instrumentation/altimeter/pressure-alt-ft");
        map["altimeter_pressure_alt_ft"] = altimeter_pressure_alt_ft;
        Variable *attitude_indicator_indicated_pitch_deg = new Variable(
                "/instrumentation/attitude-indicator/indicated-pitch-deg");
        map["attitude_indicator_indicated_pitch_deg"] = attitude_indicator_indicated_pitch_deg;
        Variable *attitude_indicator_indicated_rolL_deg = new Variable(
                "/instrumentation/attitude-indicator/indicated-roll-deg");
        map["attitude_indicator_indicated_rolL_deg"] = attitude_indicator_indicated_rolL_deg;
        Variable *attitude_indicator_internal_pitch_deg = new Variable(
                "/instrumentation/attitude-indicator/internal-pitch-deg");
        map["attitude_indicator_internal_pitch_deg"] = attitude_indicator_internal_pitch_deg;
        Variable *attitude_indicator_internal_roll_deg = new Variable(
                "/instrumentation/attitude-indicator/internal-roll-deg");
        map["attitude_indicator_internal_roll_deg"] = attitude_indicator_internal_roll_deg;
        Variable *encoder_indicated_altitude_ft = new Variable("/instrumentation/encoder/indicated-altitude-ft");
        map["encoder_indicated_altitude_ft"] = encoder_indicated_altitude_ft;
        Variable *encoder_pressure_alt_ft = new Variable("/instrumentation/encoder/pressure-alt-ft");
        map["encoder_pressure_alt_ft"] = encoder_pressure_alt_ft;
        Variable *gps_indicated_altitude_ft = new Variable("/instrumentation/gps/indicated-altitude-ft");
        map["gps_indicated_altitude_ft"] = gps_indicated_altitude_ft;
        Variable *gps_indicated_ground_speed_kt = new Variable("/instrumentation/gps/indicated-ground-speed-kt");
        map["gps_indicated_ground_speed_kt"] = gps_indicated_ground_speed_kt;
        Variable *gps_indicated_vertical_speed = new Variable("/instrumentation/gps/indicated-vertical-speed");
        map["gps_indicated_vertical_speed"] = gps_indicated_vertical_speed;
        Variable *indicated_heading_deg = new Variable("/instrumentation/heading-indicator/indicated-heading-deg");
        map["indicated_heading_deg"] = indicated_heading_deg;
        Variable *magnetic_compass_indicated_heading_deg = new Variable(
                "/instrumentation/magnetic-compass/indicated-heading-deg");
        map["magnetic_compass_indicated_heading_deg"] = magnetic_compass_indicated_heading_deg;
        Variable *slip_skid_ball_indicated_slip_skid = new Variable(
                "/instrumentation/slip-skid-ball/indicated-slip-skid");
        map["slip_skid_ball_indicated_slip_skid"] = slip_skid_ball_indicated_slip_skid;
        Variable *turn_indicator_indicated_turn_rate = new Variable(
                "/instrumentation/turn-indicator/indicated-turn-rate");
        map["turn_indicator_indicated_turn_rate"] = turn_indicator_indicated_turn_rate;
        Variable *vertical_speed_indicator_indicated_speed_fpm =
                new Variable("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
        map["vertical_speed_indicator_indicated_speed_fpm"] = vertical_speed_indicator_indicated_speed_fpm;
        Variable *flight_aileron = new Variable("/controls/flight/aileron");
        map["flight_aileron"] = flight_aileron;
        Variable *flight_elevator = new Variable("/controls/flight/elevator");
        map["flight_elevator"] = flight_elevator;
        Variable *flight_rudder = new Variable("/controls/flight/rudder");
        map["flight_rudder"] = flight_rudder;
        Variable *flight_flaps = new Variable("/controls/flight/flaps");
        map["flight_flaps"] = flight_flaps;
        Variable *engine_throttle = new Variable("/controls/engines/engine/throttle");
        map["engine_throttle"] = engine_throttle;
        Variable *current_engine_throttle = new Variable("/controls/engines/current-engine/throttle");
        map["current_engine_throttle"] = current_engine_throttle;
        Variable *switches_master_avionics = new Variable("/controls/switches/master-avionics");
        map["switches_master_avionics"] = switches_master_avionics;
        Variable *switches_starter = new Variable("/controls/switches/starter");
        map["switches_starter"] = switches_starter;
        Variable *active_engine_auto_start = new Variable("/engines/active-engine/auto-start");
        map["active_engine_auto_start"] = active_engine_auto_start;
        Variable *flight_speedbrake = new Variable("/controls/flight/speedbrake");
        map["flight_speedbrake"] = flight_speedbrake;
        Variable *c172p_brake_parking = new Variable("/sim/model/c172p/brake-parking");
        map["c172p_brake_parking"] = c172p_brake_parking;
        Variable *engine_primer = new Variable("/controls/engines/engine/primer");
        map["engine_primer"] = engine_primer;
        Variable *current_engine_mixture = new Variable("/controls/engines/current-engine/mixture");
        map["current_engine_mixture"] = current_engine_mixture;
        Variable *switches_master_bat = new Variable("/controls/switches/master-bat");
        map["switches_master_bat"] = switches_master_bat;
        Variable *switches_master_alt = new Variable("/controls/switches/master-alt");
        map["switches_master_alt"] = switches_master_alt;
        Variable *engine_rpm = new Variable("/engines/engine/rpm");
        map["engine_rpm"] = engine_rpm;
    }
    
    string simArr [35] = {simArr[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simArr[1] = "/sim/time/warp";
    simArr[2] = "/controls/switches/magnetos";
    simArr[3] = "/instrumentation/heading-indicator/offset-deg";
    simArr[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    simArr[5] = "/instrumentation/altimeter/pressure-alt-ft";
    simArr[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simArr[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    simArr[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    simArr[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    simArr[10] = "/instrumentation/encoder/indicated-altitude-ft";
    simArr[11] = "/instrumentation/encoder/pressure-alt-ft";
    simArr[12] = "/instrumentation/gps/indicated-altitude-ft";
    simArr[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    simArr[14] = "/instrumentation/gps/indicated-vertical-speed";
    simArr[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    simArr[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    simArr[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simArr[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    simArr[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simArr[20] = "/controls/flight/aileron";
    simArr[21] = "/controls/flight/elevator";
    simArr[22] = "/controls/flight/rudder";
    simArr[23] = "/controls/flight/flaps";
    simArr[24] = "/controls/engines/engine/throttle";
    simArr[25] = "/controls/engines/current-engine/throttle";
    simArr[26] = "/controls/switches/master-avionics";
    simArr[27] = "/controls/switches/starter";
    simArr[28] = "/engines/active-engine/auto-start";
    simArr[29] = "/controls/flight/speedbrake";
    simArr[30] = "/sim/model/c172p/brake-parking";
    simArr[31] = "/controls/engines/engine/primer";
    simArr[32] = "/controls/engines/current-engine/mixture";
    simArr[33] = "/controls/switches/master-bat";
    simArr[34] = "/controls/switches/master-alt";
    simArr[35] = "/engines/engine/rpm";}


public:
    unordered_map<string, Variable*> getMap() {
        return this->map;
    }

    void addValuesFromSimToSymbolTable(vector<string> splitValues) {
        //std::string::size_type sz;     // alias of size_t
        for (int i = 0; i < splitValues.size(); i++) {
            //double splVal = std::stod (splitValues[i],&sz);
            this->map[simArr[i]] = new Variable(simArr[i], atof(splitValues[i]), 0);
        }
    }
};

#endif //FLIGHTSIMULATOR_SYMBOLTABLE_H