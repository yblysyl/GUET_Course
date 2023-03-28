LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY DECODER IS
PORT(
    I9,I8:IN STD_LOGIC;
    Y0,Y1,Y2,Y3: OUT STD_LOGIC
);
END DECODER;
ARCHITECTURE A OF DECODER IS
BEGIN
    PROCESS
    BEGIN
        IF(I9='0' AND I8='0') THEN
            Y0<='1';
            Y1<='0';
            Y2<='0';
            Y3<='0';
        ELSIF(I9='0' AND I8='1') THEN
            Y0<='0';
            Y1<='1';
            Y2<='0';
            Y3<='0';
        ELSIF(I9='1' AND I8='0') THEN
            Y0<='0';
            Y1<='0';
            Y2<='1';
            Y3<='0';
        ELSE
            Y0<='0';
            Y1<='0';
            Y2<='0';
            Y3<='1';
        END IF;
    END PROCESS;
END A;


