#include <iostream>
#include <string>

class Message
{
public:
  Message(); // Constructeur
  void Show() const; // Affichage
  //setter global
  void SET(std::string id, int type, int repeat_indic, double mmsi, int navig_statu, int rate_of_turn, int speed, int pos_accuracy, double longitude, double latitude, int course, int heading);
  //setter
  void setId(string id);
  void setType(int type);
  void setRepeat_indic(int repeat_indic);
  void setMmsi(double mmsi);
  void setNavig_statu(int navig_statu);
  void setRate_of_turn(int rate_of_turn);
  void setSpeed(int speed);
  void setPos_accuracy(int pos_accuracy);
  void setLongitude(double longitude);
  void setLatitude(double latitude);
  void setCourse(int course);
  void setHeading(int heading);
  //getter
  void getId() const;
  void getType() const;
  void getRepeat_indic() const;
  void getMmsi() const;
  void getNavig_statu() const;
  void getRate_of_turn() const;
  void getSpeed() const;
  void getPos_accuracy() const;
  void getLongitude() const;
  void getLatitude() const;
  void getCourse() const;
  void getHeading() const;

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
