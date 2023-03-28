LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY MUX4_2 IS 
PORT( 
    R0,R1,R2,R3:IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    I9,I8:IN STD_LOGIC;
    Y:OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
);
END MUX4_2;
ARCHITECTURE A OF MUX4_2 IS
BEGIN
    PROCESS
    BEGIN
        IF(I9='0' AND I8='0') THEN
            Y<=R0;
        ELSIF(I9='0' AND I8='1') THEN
            Y<=R1;
        ELSIF(I9='1' AND I8='0') THEN
            Y<=R2;
        ELSE
            Y<=R3;
        END IF;
    END PROCESS;
END A;


