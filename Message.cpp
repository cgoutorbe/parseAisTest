#include <iostream>
#include <string>
#include "Message.h"

using namespace std;

Message::Message():m_id("NOM#"), m_type(0), m_repeat_indic(0), m_mmsi(0), m_navig_statu(0),
m_rate_of_turn(0), m_speed(0), m_pos_accuracy(0), m_longitude(0), m_latitude(0), m_course(0), m_heading(0)
{
}

void Message::Show() const
{
  cout<<"\nmessage type = \t\t"<< this->m_type;
	cout<<"\nrepeat indicator = \t"<< this->m_repeat_indic;
	cout<< setfill('0')<< "\nMMSI = \t\t\t" << setw(9) << this->m_mmsi;
	cout<<"\nnavagation status = \t"<< this->m_navig_statu;
	cout<<"\nrate of turn = \t\t"<< this->m_rate_of_turn;
	cout<<"\nspeed over ground = \t"<< this->m_speed;
	cout<<"\nposition accuracy = \t"<< this->m_pos_accuracy;
	cout<< fixed << "\nlongitude = \t\t"<< this->m_longitude;
	cout<< fixed << "\nlatitude = \t\t"<< this->m_latitude;
	cout<<"\ncourse over ground = \t"<< this->m_course;
	cout<<"\ntrue heading = \t\t"<< this->m_heading;
}

void Message::SET(Message m, string id, int type, int repeat_indic, double mmsi, int navig_statu, int rate_of_turn, int speed, int pos_accuracy, double longitude, double latitude, int course, int){
  this->m_id = id
  this->m_type = type
  this->m_repeat_indic = repeat_indic
  this->m_mmsi = mmsi
  this->m_navig_statu = navig_statu
  this->m_rate_of_turn = rate_of_turn
  this->m_speed = speed
  this->m_pos_accuracy = pos_accuracy
  this->m_longitude = longitude
  this->m_latitude = latitude
  this->m_course = course
  this->m_heading = heading
}
