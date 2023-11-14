# configure logger for DB queries
import logging

logger = logging.getLogger(__name__)

def get_user_ip_address(request):
    """Gets the IP address of the user who submitted the POST request

    Warning
    -------
    request.META.get('REMOTE_ADDR') is easily spoofed by malicious users,
    and should not be used for security purposes.
    """

    ip_address = request.META.get("REMOTE_ADDR")
    return ip_address


def log_query_as_INFO(
    userIP: str, type: str, time: str
):
    logger.info(
        "User IP: {} | type: {} | time: {}".format(
            userIP,
            type,
            time,
        )
    )