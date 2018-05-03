#!/usr/bin/env python
import sys
import termios
import contextlib
import rospy
from std_msgs.msg import String


@contextlib.contextmanager
def raw_mode(file):
    old_attrs = termios.tcgetattr(file.fileno())
    new_attrs = old_attrs[:]
    new_attrs[3] = new_attrs[3] & ~(termios.ECHO | termios.ICANON)
    try:
        termios.tcsetattr(file.fileno(), termios.TCSADRAIN, new_attrs)
        yield
    finally:
        termios.tcsetattr(file.fileno(), termios.TCSADRAIN, old_attrs)

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()

def main():
    print 'exit with ^C or ^D'
    with raw_mode(sys.stdin):
        try:
            while True:
                keypress = sys.stdin.read(1)
                if not keypress or keypress == chr(4):
                    break

                keystring = '%02x' %  ord(keypress)
                #print keystring

                if keystring == '64':
                    print 'right' #keystring
                    
                if keystring == '61':
                    print 'left'
                if keystring == '77':
                    print 'forward'
                if keystring == '73':
                    print 'back'
                if keystring == '20':
                    print 'up'
                if keystring == '7a':
                    print 'down'



        except (KeyboardInterrupt, EOFError):
            pass


if __name__ == '__main__':
    main()


#'%02x' % 