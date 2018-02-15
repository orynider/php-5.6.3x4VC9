--TEST--
IBM-DB2: db2_fetch_assoc() - nested selects 1
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($db,$username,$password);

$result = db2_exec($conn, "select * from staff");

while ($row = db2_fetch_assoc($result)) 
{
   printf ("%5d  ",$row['ID']);
   printf ("%-10s ",$row['NAME']);
   printf ("%5d ",$row['DEPT']);
   printf ("%-7s ",$row['JOB']);
   printf ("%5d ", $row['YEARS']);
   printf ("%15s ", $row['SALARY']);
   printf ("%10s ", $row['COMM']);
   print "\n";
   $result2 = db2_exec($conn,"select * from department where substr(deptno,1,1) in ('A','B','C','D','E')");
   while ($row2 = db2_fetch_assoc($result2)) 
   {
      printf ("\t\t%3s %29s %6s %3s %-16s\n",
      $row2['DEPTNO'], $row2['DEPTNAME'], $row2['MGRNO'],
      $row2['ADMRDEPT'], $row2['LOCATION']);	
      $result3 = db2_exec($conn,"select count(*) from sales");
   }
}

?>
--EXPECT--

   10  Sanders       20 Mgr         7        18357.50            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   20  Pernal        20 Sales       8        18171.25     612.45 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   30  Marenghi      38 Mgr         5        17506.75            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   40  O'Brien       38 Sales       6        18006.00     846.55 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   50  Hanes         15 Mgr        10        20659.80            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   60  Quigley       38 Sales       0        16808.30     650.25 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   70  Rothman       15 Sales       7        16502.83    1152.00 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   80  James         20 Clerk       0        13504.60     128.20 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
   90  Koonitz       42 Sales       6        18001.75    1386.70 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  100  Plotz         42 Mgr         7        18352.80            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  110  Ngan          15 Clerk       5        12508.20     206.60 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  120  Naughton      38 Clerk       0        12954.75     180.00 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  130  Yamaguchi     42 Clerk       6        10505.90      75.60 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  140  Fraye         51 Mgr         6        21150.00            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  150  Williams      51 Sales       6        19456.50     637.65 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  160  Molinare      10 Mgr         7        22959.20            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  170  Kermisch      15 Clerk       4        12258.50     110.10 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  180  Abrahams      38 Clerk       3        12009.75     236.50 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  190  Sneider       20 Clerk       8        14252.75     126.50 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  200  Scoutten      42 Clerk       0        11508.60      84.20 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  210  Lu            10 Mgr        10        20010.00            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  220  Smith         51 Sales       7        17654.50     992.80 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  230  Lundquist     51 Clerk       3        13369.80     189.65 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  240  Daniels       10 Mgr         5        19260.25            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  250  Wheeler       51 Clerk       6        14460.00     513.30 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  260  Jones         10 Mgr        12        21234.00            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  270  Lea           66 Mgr         9        18555.50            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  280  Wilson        66 Sales       9        18674.50     811.50 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  290  Quill         84 Mgr        10        19818.00            
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  300  Davis         84 Sales       5        15454.50     806.10 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  310  Graham        66 Sales      13        21000.00     200.30 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  320  Gonzales      66 Sales       4        16858.20     844.00 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  330  Burke         66 Clerk       1        10988.00      55.50 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  340  Edwards       84 Sales       7        17844.00    1285.00 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 
  350  Gafney        84 Clerk       5        13030.50     188.00 
		A00  SPIFFY COMPUTER SERVICE DIV. 000010 A00                 
		B01                      PLANNING 000020 A00                 
		C01            INFORMATION CENTER 000030 A00                 
		D01            DEVELOPMENT CENTER        A00                 
		D11         MANUFACTURING SYSTEMS 000060 D01                 
		D21        ADMINISTRATION SYSTEMS 000070 D01                 
		E01              SUPPORT SERVICES 000050 A00                 
		E11                    OPERATIONS 000090 E01                 
		E21              SOFTWARE SUPPORT 000100 E01                 

