GPP=g++
CC=${GPP}
GPPFLAGS=-Wall -Werror

EXEC=airwatcher
OBJ=main.o Sensor.o Attribute.o Measurement.o

${EXEC}: ${OBJ}
	${GPP} ${GPPFLAGS} -o ${EXEC} $^

%.o: %.cpp
	${GPP} ${GPPFLAGS} -o $@ -c $^

clean:
	rm -f ${EXEC} ${OBJ}
