<?php
namespace Crypto;

$algorithm = 'aes-256-cbc';

if (!Cipher::hasAlgorithm($algorithm)) {
	die("Algorithm $algorithm not found" . PHP_EOL);
}

try {
	$cipher = new Cipher($algorithm);

	// Algorithm method for retrieving algorithm
	echo "Algorithm: " . $cipher->getAlgorithmName() . PHP_EOL;

	// Params
	$key_len = $cipher->getKeyLength();
	$iv_len = $cipher->getIVLength();
	
	echo "Key length: " . $key_len . PHP_EOL;
	echo "IV length: "  . $iv_len . PHP_EOL;
	echo "Block size: " . $cipher->getBlockSize() . PHP_EOL;

	// This is just for this example. You should never use such key and IV!
	$key = str_repeat('x', $key_len);
	$iv = str_repeat('i', $iv_len);

	// Test data
	$data1 = "Test";
	$data2 = "Data";
	$data = $data1 . $data2;

	// Simple encryption
	$sim_ct = $cipher->encrypt($data, $key, $iv);
	
	// init/update/finish encryption
	$cipher->encryptInit($key, $iv);
	$iuf_ct  = $cipher->encryptUpdate($data1);
	$iuf_ct .= $cipher->encryptUpdate($data2);
	$iuf_ct .= $cipher->encryptFinish();

	// Raw data output (used base64 format for printing)
	echo "Ciphertext (sim): " . base64_encode($sim_ct) . PHP_EOL;
	echo "Ciphertext (iuf): " . base64_encode($iuf_ct) . PHP_EOL;
	// $iuf_out == $sim_out
	$ct = $sim_ct;

	// Another way how to create a new cipher object (using the same algorithm and mode)
	$cipher = Cipher::aes(Cipher::MODE_CBC, 256);

	// Simple decryption
	$sim_text = $cipher->decrypt($ct, $key, $iv);
	
	// init/update/finish decryption
	$cipher->decryptInit($key, $iv);
	$iuf_text = $cipher->decryptUpdate($ct);
	$iuf_text .= $cipher->decryptFinish();

	// Raw data output ($iuf_out == $sim_out)
	echo "Text (sim): " . $sim_text . PHP_EOL;
	echo "Text (iuf): " . $iuf_text . PHP_EOL;
}
catch (AlgorithmException $e) {
	echo $e->getMessage() . PHP_EOL;
}
