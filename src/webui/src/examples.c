#include <kore.h>
#include <http.h>
#include <assets.h>
#include <template.h>

int websocket_example(struct http_request *req) {
	template_t tmpl;
	attrlist_t attributes;
	struct kore_buf *buf;
	char *address;

	// allocate output buffer
	buf = kore_buf_alloc(1024*1000);

	// load template
	template_load
		(asset_websocket_html, asset_len_websocket_html, &tmpl);
	attributes = attrinit();

	address = getenv("address");
	if(!address) address = "127.0.0.1";

	attrset(attributes, "address", address);


	template_apply(&tmpl,attributes,buf);

	http_response_header(req, "content-type", "text/html");
	http_response(req, 200, buf->data, buf->offset);


	template_free(&tmpl);
	attrfree(attributes);

	kore_buf_free(buf);

	return(KORE_RESULT_OK);
}
                     