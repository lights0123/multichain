const { expect } = require('chai');
const { spawn } = require('child_process');
const { join } = require('path');

describe('actumcrypto-util', function() {
	it('should be able to create a blockchain', function(done) {
		spawn(join(__dirname, '../actumcrypto/actumcrypto-util', ['create test']).on('close', function(code) => {
			expect(code).to.be(0);
			done();
		});
	});
});
