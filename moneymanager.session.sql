USE moneymanager;

DROP TABLE statements; --USE THIS IF YOU NEED TO REMAKE YOUR TABLE AND CLEAR CONTENTS

CREATE TABLE statements(
    id INT AUTO_INCREMENT PRIMARY KEY,
    description TEXT(255) NOT NULL,
    withdrawals DECIMAL(10, 2) NOT NULL,
    deposits DECIMAL(10, 2) NOT NULL
);

SELECT * FROM statements;

SELECT DESCRIPTION FROM statements;
