require File.expand_path('../../../../../spec_helper', __FILE__)
require 'net/http'
require File.expand_path('../fixtures/http_server', __FILE__)

describe "Net::HTTP.Proxy" do
  it "returns a new subclass of Net::HTTP" do
    Net::HTTP.Proxy("127.0.0.1").should < Net::HTTP
  end

  it "returns Net::HTTP when the passed address is nil" do
    Net::HTTP.Proxy(nil).should == Net::HTTP
  end

  it "sets the returned subclasses' proxy options based on the passed arguments" do
    http_with_proxy = Net::HTTP.Proxy("127.0.0.1", 1234, "rspec", "rocks")
    http_with_proxy.proxy_address.should == "127.0.0.1"
    http_with_proxy.proxy_port.should eql(1234)
    http_with_proxy.proxy_user.should == "rspec"
    http_with_proxy.proxy_pass.should == "rocks"
  end
end

describe "Net::HTTP#proxy?" do
  describe "when self is no proxy class instance" do
    it "returns false" do
      Net::HTTP.new("127.0.0.1", NetHTTPSpecs.server_port).proxy?.should be_false
    end
  end

  describe "when self is a proxy class instance" do
    it "returns false" do
      http_with_proxy = Net::HTTP.Proxy("127.0.0.1", 1234, "rspec", "rocks")
      http_with_proxy.new("127.0.0.1", NetHTTPSpecs.server_port).proxy?.should be_true
    end
  end
end
