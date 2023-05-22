GPP=g++
CC=${GPP}
GPPFLAGS=-Wall 

EXEC=airwatcher
OBJ=main.o Sensor.o Attribute.o Measurement.o Controller.o User.o

${EXEC}: ${OBJ}
	${GPP} ${GPPFLAGS} -o ${EXEC} $^

%.o: %.cpp
	${GPP} ${GPPFLAGS} -o $@ -c $^

clean:
	rm -f ${EXEC} ${OBJ}
