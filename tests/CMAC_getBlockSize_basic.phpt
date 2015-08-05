--TEST--
Crypto\CMAC::getBlockSize basic usage.
--FILE--
<?php
$key = pack('H*', '2b7e151628aed2a6abf7158809cf4f3c');

$cmac = new Crypto\CMAC($key, 'aes-128-cbc');
echo $cmac->getBlockSize() . "\n";
echo "SUCCESS\n";
?>
--EXPECT--
16
SUCCESS
