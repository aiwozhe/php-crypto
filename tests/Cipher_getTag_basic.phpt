--TEST--
Crypto\Cipher::getTag basic usage.
--SKIPIF--
<?php if (!Crypto\Cipher::hasMode(Crypto\Cipher::MODE_GCM)) die("Skip: GCM mode not defined (update OpenSSL version)"); ?>
--FILE--
<?php
$key = str_repeat('x', 32);
$iv = str_repeat('i', 16);

$data = str_repeat('a', 16);

$cipher = new Crypto\Cipher('aes-256-gcm');

try {
    $cipher->getTag(16);
}
catch (Crypto\AlgorithmException $e) {
	if ($e->getCode() == Crypto\AlgorithmException::CIPHER_TAG_GETTER_FLOW) {
		echo "FLOW\n";
	}
}

// init first
echo bin2hex($cipher->encrypt($data, $key, $iv)) . "\n";
echo bin2hex($cipher->getTag(16)) . "\n";


?>
--EXPECT--
FLOW
622070d3bea6f720943d1198a7e6afa5
ed39e13f9a9fdf19036ad2f1ed5d2d1f
