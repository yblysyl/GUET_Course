LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY PSW IS
PORT(
    LDPSW:IN STD_LOGIC;
    CF_IN,ZF_IN,SF_IN:IN STD_LOGIC;
    CF,ZF,SF:OUT STD_LOGIC
);
END PSW;
ARCHITECTURE A OF PSW IS
BEGIN
    PROCESS(LDPSW)
    BEGIN
        IF(LDPSW'EVENT AND LDPSW='1') THEN
            CF<=CF_IN;
            ZF<=ZF_IN;
            SF<=SF_IN;
        END IF;
    END PROCESS;
END A;
  


