LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
ENTITY ALU IS
PORT(
    X:IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    Y:IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    S2,S1,S0:IN STD_LOGIC;
    ALUOUT:OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    CF,ZF,SF:OUT STD_LOGIC
);
END ALU;
ARCHITECTURE A OF ALU IS
SIGNAL XX,YY,TEMP:STD_LOGIC_VECTOR(8 DOWNTO 0);
BEGIN
    PROCESS
    BEGIN
        IF(S2='0' AND S1='0' AND S0='0') THEN  -- add
            XX<='0'&X;
            YY<='0'&Y;
            TEMP<=XX+YY;
            ALUOUT<=TEMP(7 DOWNTO 0);
            CF<=TEMP(8);
            SF<=TEMP(7);
            IF(TEMP="100000000" OR TEMP="000000000") THEN
                ZF<='1';
            ELSE
                ZF<='0';
            END IF;
         ELSIF(S2='0' AND S1='0' AND S0='1') THEN   -- cmp
            ALUOUT<=X-Y;
            IF(X<Y) THEN
                CF<='1';
                ZF<='0';
                SF<='1';
            ELSIF(X=Y) THEN
                CF<='0';
                ZF<='1';
                SF<='0';
            ELSE
                CF<='0';
                ZF<='0';
                SF<='0';
            END IF;
        ELSIF(S2='0' AND S1='1' AND S0='0') THEN  --INC
             YY<='0'&Y;
             TEMP<=YY+1;
             ALUOUT<=TEMP(7 DOWNTO 0);
             CF<=TEMP(8);
             SF<=TEMP(7);
             IF(TEMP="100000000"OR TEMP="000000000") THEN
                 ZF<='1';
             ELSE
                 ZF<='0';
             END IF;
         ELSIF(S2='0' AND S1='1' AND S0='1') THEN --DEC
             YY<='0'&Y;
             TEMP<=YY-1;
             ALUOUT<=TEMP(7 DOWNTO 0);
             CF<=TEMP(8);
             SF<=TEMP(7);
             IF(TEMP="100000000"OR TEMP="000000000") THEN
                 ZF<='1';
             ELSE
                 ZF<='0';
             END IF;
         ELSIF(S2='1' AND S1='0' AND S0='0') THEN  --NEG
             YY<='0'&Y;
             TEMP<=0-Y;
             ALUOUT<=TEMP(7 DOWNTO 0);
             CF<=TEMP(8);
             SF<=TEMP(7);
             IF(TEMP="100000000"OR TEMP="000000000") THEN
                 ZF<='1';
             ELSE
                 ZF<='0';
             END IF;
          ELSIF(S2='1' AND S1='0' AND S0='1') THEN --TEST
             YY<='0'&Y;
             TEMP<=YY-0;
             ALUOUT<=TEMP(7 DOWNTO 0);
             CF<=TEMP(8);
             SF<=TEMP(7);
             IF(TEMP="100000000"OR TEMP="000000000") THEN
                 ZF<='1';
             ELSE
                 ZF<='0';
             END IF;
         ELSIF(S2='1' AND S1='1' AND S0='0') THEN  --Rd->BUS
             ALUOUT<=Y;
         ELSE
             ALUOUT<="00000000";
             CF<='0';
             ZF<='0';
             SF<='0';
         END IF;
     END PROCESS;
END A;


             


