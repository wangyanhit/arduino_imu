/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */
#define USE_USBCON
#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

#include <Wire.h>// include MPU9255 library
#include <MPU9255.h>// include MPU9255 library


ros::NodeHandle nh;
std_msgs::Int16MultiArray msg;

ros::Publisher chatter("chatter", &msg);

MPU9255 mpu;
int16_t cnt = 0;
void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  Wire.begin();//initialize I2C interface
  mpu.init();// Initialize MPU9255 chip
}

void loop()
{
  int16_t a[7];
  mpu.read_acc();// read data from accelerometer
  mpu.read_gyro();// get data from gyroscope
  mpu.read_mag();// get data from the magnetometer
  a[1] = mpu.ax;
  a[2] = mpu.ay;
  a[3] = mpu.az;
  a[4] = mpu.gx;
  a[5] = mpu.gy;
  a[6] = mpu.gz;
  a[0] = cnt++;
  msg.data = a;
  msg.data_length = 7;
  chatter.publish(&msg);
  nh.spinOnce();
  delay(50);
}
