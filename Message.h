#include <iostream>
#include <string>

class Message
{
public:
  Message(); // Constructeur
  void Show() const; // Affichage
  void SET(Mstd::string id, int type, int repeat_indic, double mmsi, int navig_statu, int rate_of_turn, int speed, int pos_accuracy, double longitude, double latitude, int course, int heading);

private:
  std::string m_id;
  int m_type;
  int m_repeat_indic;
  double m_mmsi;
  int m_navig_statu;
  int m_rate_of_turn;
  int m_speed;
  int m_pos_accuracy;
  double m_longitude;
  double m_latitude;
  int m_course;
  int m_heading;
};
