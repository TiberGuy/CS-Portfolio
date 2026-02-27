//Contact.java
public class Contact {
  private final String contactId;
  private String firstName;
  private String lastName;
  private String phone;
  private String address;

  public Contact(String contactId, String firstName, String lastName, String phone, String address) {
    validateContactId(contactId);
    validateFirstName(firstName);
    validateLastName(lastName);
    validatePhone(phone);
    validateAddress(address);

    this.contactId = contactId;
    this.firstName = firstName;
    this.lastName = lastName;
    this.phone = phone;
    this.address = address;
  }

  public String getContactId() {
    return contactId;
  }

  public String getFirstName() {
    return firstName;
  }

  public String getLastName() {
    return lastName;
  }

  public String getPhone() {
    return phone;
  }

  public String getAddress() {
    return address;
  }

  public void setFirstName(String firstName) {
    validateFirstName(firstName);
    this.firstName = firstName;
  }

  public void setLastName(String lastName) {
    validateLastName(lastName);
    this.lastName = lastName;
  }

  public void setPhone(String phone) {
    validatePhone(phone);
    this.phone = phone;
  }

  public void setAddress(String address) {
    validateAddress(address);
    this.address = address;
  }

  private static void validateContactId(String contactId) {
    if (contactId == null) throw new IllegalArgumentException("contactId must not be null");
    if (contactId.length() > 10) throw new IllegalArgumentException("contactId must be <= 10 characters");
    if (contactId.isBlank()) throw new IllegalArgumentException("contactId must not be blank");
  }

  private static void validateFirstName(String firstName) {
    if (firstName == null) throw new IllegalArgumentException("firstName must not be null");
    if (firstName.length() > 10) throw new IllegalArgumentException("firstName must be <= 10 characters");
  }

  private static void validateLastName(String lastName) {
    if (lastName == null) throw new IllegalArgumentException("lastName must not be null");
    if (lastName.length() > 10) throw new IllegalArgumentException("lastName must be <= 10 characters");
  }

  private static void validatePhone(String phone) {
    if (phone == null) throw new IllegalArgumentException("phone must not be null");
    if (!phone.matches("\\d{10}")) throw new IllegalArgumentException("phone must be exactly 10 digits");
  }

  private static void validateAddress(String address) {
    if (address == null) throw new IllegalArgumentException("address must not be null");
    if (address.length() > 30) throw new IllegalArgumentException("address must be <= 30 characters");
  }
}
